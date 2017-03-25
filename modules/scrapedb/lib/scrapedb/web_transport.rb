require 'highline'
require "selenium/webdriver"

class Scrapedb::WebTransport

    LOGIN_PAGE = 'https://santodomingosavio-salesianos-madrid.educamos.com/'
    LIST_PAGE  = 'https://santodomingosavio-salesianos-madrid.educamos.com/Evaluacion/PasarLista'

    attr_reader :login, :passw, :driver, :connected
    @phis_date

    def initialize
        @connected = false
    end

    def scrape_levels
        levels = Array.new
        go_to LIST_PAGE
        niveles = @driver.find_element(:id => 'cmbNivelesEducativos')
        options = niveles.find_elements(:tag_name => 'option')
        options.each do |option|
            attrib = Hash.new
            attrib = @driver.execute_script('var items = {}; for (index = 0; index < arguments[0].attributes.length; ++index) { items[arguments[0].attributes[index].name] = arguments[0].attributes[index].value  }; return items;', option)
            attrib["text"] = option.text
            levels.push attrib
        end
        levels
    end

    def scrape_users_from level
        go_to LIST_PAGE

        unless @phis_date
            @date = '16/03/2017'
            @driver.find_element(:id => 'fecha').clear
            @driver.find_element(:id => 'fecha').send_keys '16/03/2017'
            sleep 1
        end

        Selenium::WebDriver::Support::Select.new(@driver.find_element(:id => 'cmbNivelesEducativos')).select_by(:text, level['text'])
        sleep 0.7
        Selenium::WebDriver::Support::Select.new(@driver.find_element(:id => 'MateriaId')).select_by(:index, "1")

        sleep 0.5

        users = []
        lista = @driver.find_element(:id => 'gridPasarLista')
        stdnts = lista.find_elements(:tag_name => 'tr')
        stdnts.each do |student|
            if student.attribute('data-uid')
                user = Hash.new
                user['data-uid'] = student.attribute('data-uid')
                lin = student.find_element(:xpath, "//tr[@data-uid = \"#{user['data-uid']}\"]//a")
                user['id'] = lin.attribute('id')
                user['name'] = lin.text
                users.push user
            end
        end
        users
    end


    private

    def go_to url
        login unless @connected
        return if url == @driver.current_url
        @driver.navigate.to url
        sleep 3
    end

    def ask_credentials
        cli = HighLine.new
        @login = cli.ask('Login: ')
        @passw = cli.ask('Password: ') { |q| q.echo = "*"  }
    end

    def got_credentials?
        @login and @passw
    end

    def login
        return if @connected
        ask_credentials unless got_credentials?
        @driver = Selenium::WebDriver.for :firefox
        @driver.navigate.to LOGIN_PAGE
        @driver.find_element(:id => 'NombreUsuario').send_keys @login
        @driver.find_element(:id => 'Clave').send_keys @passw
        @driver.find_element(:tag_name => 'form').submit
        @connected = true
        sleep 10
    end


end

require "selenium/webdriver"

class Scrapedb::Educamos

    LOGIN_PAGE = 'https://santodomingosavio-salesianos-madrid.educamos.com/'
    LIST_PAGE  = 'https://santodomingosavio-salesianos-madrid.educamos.com/Evaluacion/PasarLista'

    attr_reader :login, :pass, :driver
    attr_accessor :levels

    def initialize(login, pass)
        @login, @pass = login, pass
        @levels = []
        @driver = Selenium::WebDriver.for :firefox

        @driver.navigate.to LOGIN_PAGE
        @driver.find_element(:id => 'NombreUsuario').send_keys @login
        @driver.find_element(:id => 'Clave').send_keys @pass
        @driver.find_element(:tag_name => 'form').submit
    end

    def scrape_levels
        @driver.navigate.to LIST_PAGE
        sleep 4
        niveles = @driver.find_element(:id => 'cmbNivelesEducativos')
        options = niveles.find_elements(:tag_name => 'option')
        options.each do |option|
            attrib = Hash.new
            attrib = @driver.execute_script('var items = {}; for (index = 0; index < arguments[0].attributes.length; ++index) { items[arguments[0].attributes[index].name] = arguments[0].attributes[index].value  }; return items;', option)
            attrib["text"] = option.text
            @levels.push attrib
        end
        @levels
    end

end

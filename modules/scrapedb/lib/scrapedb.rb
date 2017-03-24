require 'mechanize'

class Scrapedb

    LOGIN_PAGE = "https://sso2.educamos.com/Autenticacion/Acceder?ReturnUrl=%2fissue%2fwsfed%3fwa%3dwsignin1.0%26wtrealm%3dhttps%253a%252f%252fsantodomingosavio-salesianos-madrid.educamos.com%252f%26wctx%3drm%253d0%2526id%253dpassive%2526ru%253d%25252f%26wct%3d2017-03-23T18%253a52%253a31Z&wa=wsignin1.0&wtrealm=https%3a%2f%2fsantodomingosavio-salesianos-madrid.educamos.com%2f&wctx=rm%3d0%26id%3dpassive%26ru%3d%252f&wct=2017-03-23T18%3a52%3a31Z"

    @login
    @pass
    @agent

    def initialize(login, pass)
        @login, @pass = login, pass
        puts "Scrapedb is running on behalf of #{@login}"
        @agent = Mechanize.new
        login_result = @agent.get(LOGIN_PAGE) do |page|
            page.form_with(:method => 'post') do |login|
                login.NombreUsuario = @login
                login.Clave = @pass
            end.submit
        end

       # puts login_result.inspect
    end
end


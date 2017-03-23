class Scrapedb

    @login
    @pass

    def initialize(login, pass)
        @login, @pass = login, pass
        puts "Scrapedb is running on behalf of #{@login}"
    end
end


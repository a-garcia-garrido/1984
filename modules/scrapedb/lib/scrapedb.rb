require "scrapedb/version"
require "scrapedb/educamos"
require 'highline'
require 'yaml'
require 'fileutils'

class Scrapedb

    OUTPUT_DIR = File.join(ENV['HOME'], '.scrapedb/output')
    LEVEL_F    = 'levels.yml'

    attr_reader :login, :passw, :levels, :connection

    def initialize
        FileUtils.mkdir_p OUTPUT_DIR unless Dir.exists? OUTPUT_DIR
        fetch_levels
        #fetch_users @level
    end

    def fetch_levels
        level_fn = File.join(OUTPUT_DIR, LEVEL_F)
        if (!File.file?(level_fn))
            login unless @connection
            @levels = @connection.scrape_levels
            File.open(level_fn, 'w') { |f| f.write @levels.to_yaml }
        end
        @levels ||= YAML::load_file(level_fn)
    end

    def fecth_users(level)
    end

    private

    def ask_credentials
        cli = HighLine.new
        @login = cli.ask('Login: ')
        @passw = cli.ask('Password: ') { |q| q.echo = "*"  }
    end

    def got_credentials?
        @login and @passw
    end

    def login
        ask_credentials unless got_credentials?
        @connection = Educamos.new(@login, @passw)
        sleep 10
    end

end

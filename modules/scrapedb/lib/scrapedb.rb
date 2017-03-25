require "scrapedb/version"
require "scrapedb/web_transport"
require 'yaml'
require 'fileutils'

class Scrapedb

    OUTPUT_DIR       = File.join(ENV['HOME'], '.scrapedb/output')
    LEVEL_F          = 'levels.yml'
    USERS_F          = 'users.yml'
    LEVEL_USERS_F    = 'levels_users.yml'

    attr_reader :levels, :connection, :user_list, :level_users

    def initialize
        FileUtils.mkdir_p OUTPUT_DIR unless Dir.exists? OUTPUT_DIR
        @connection = WebTransport.new
        @user_list = Array.new
        fetch_users @level
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


    def fetch_users(levels)

        users_fn        = File.join(OUTPUT_DIR, USERS_F)
        levels_users_fn = File.join(OUTPUT_DIR, LEVEL_USERS_F)

        if (!(File.file? users_fn and File.file? levels_users_fn))
            levels ||= fetch_levels
            @level_users = Marshal.load(Marshal.dump(levels))

            @level_users.each do |level|
                if level.has_key? 'value' and not level['value'].empty? and not level.has_key? 'disabled'
                    begin
                    users = @connection.scrape_users_from level
                    @user_list += users
                    level['users'] = users
                    $stderr.print "."
                    rescue Exception => e
                        $stderr.puts e.inspect
                        $stderr.puts "\nProblem with level #{level['text']}"
                    end
                end
            end

            File.open(users_fn, 'w')        { |f| f.write @user_list.to_yaml }
            File.open(levels_users_fn, 'w') { |f| f.write @levels_users.to_yaml }
        end

        @level_users ||= YAML::load_file(levels_users_fn)
        @user_list ||= YAML::load_file(users_fn)
    end

end

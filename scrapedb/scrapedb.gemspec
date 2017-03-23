Gem::Specification.new do |s|
    s.name = 'scrapedb'
    s.version = '0.0.0'
    s.date = '2017-03-23'
    s.executables << 'scrapedb'
    s.summary = "Scrapes pictures"
    s.description = 'Scrapes a web for pictures and names'
    s.authors = ['imasen']
    s.email = 'any@any.any'
    s.files = ["lib/scrapedb.rb"]
    s.homepage = 'http://any.hall'
    s.license = 'GPL'
    s.add_runtime_dependency "highline", "~> 1.7"
    s.add_runtime_dependency "mechanize", "~> 2"
end


require 'pry-byebug'
require 'octokit'
require 'sdk/ci'

REPO_NAME = "tenjin/tenjin-ios-sdk"

INTERNAL_REPO = "tenjin/tenjin-ios-sdk"
INTERNAL_REPO_RELEASE_NOTES = "README.md"
COCOAPODS_FILE = "TenjinSDK.podspec"

RELEASE_NOTES = "RELEASE_NOTES.md"
RELEASE_BRANCH = "master"

RELEASE_ASSETS = %w(libTenjinSDK.a libTenjinSDKUniversal.a TenjinSDK.h)

DELAY = 3

def get_release
  puts "token: "
  puts ENV["GITHUB_TOKEN"]
  @client = Octokit::Client.new(access_token: ENV["GITHUB_TOKEN"])
  puts @client
  puts INTERNAL_REPO

  release = @client.latest_release INTERNAL_REPO
  notes, version, assets = release[:body], release[:tag_name], release[:assets]

  assets.each do |a|
    f = @client.release_asset(a[:url], accept: "application/octet-stream")
    File.open(a[:name],"wb"){|file| file << f}
  end

  [version,  notes]
end

def update_pod(version)
  version_regex = /^\s*s\.version/
  extracted_semver = version.scan(/(\d+\.\d+\.\d+)/).flatten.first
  new_version = "  s.version      = \"#{extracted_semver}\""

  Sdk::Ci::Util.replace_line_in_file COCOAPODS_FILE, version_regex,  new_version
end

def commit_and_tag(version)
  Sdk::Ci::Github.commit_and_push version, RELEASE_BRANCH unless ENV["DRY_RUN"]
end

def push_pod
  #cocoapods internally depends upon github tags on the remote repo
  puts "Giving tags a chance to propogate on github..."
  sleep DELAY

  #hand over process to cocoapods push
  exec "bundle exec pod trunk push" unless ENV["DRY_RUN"]
end

def update_release_notes tag
  file = @client.contents INTERNAL_REPO, path: INTERNAL_REPO_RELEASE_NOTES, ref: tag

  #extract file contents and remove newlines
  file_contents = file[:content].lines.map(&:chomp).join

  #decode into array of utf8 string
  file_text = Base64.decode64(file_contents).lines

  #remove until we get to the first release description
  release_notes = file_text.drop_while {|l| not l =~ /^v\d+\.\d+\.\d+/ }

  File.open(RELEASE_NOTES,"w") {|f| f << release_notes.join }
end

def update_readme version
  title_regex = /Tenjin iOS SDK v\d+\.\d+\.\d+/

  #write out version in readme
  Sdk::Ci::Util.replace_line_in_file "README.md", title_regex, "Tenjin iOS SDK v#{version}"
end

def push_github_release version, description

  Sdk::Ci::Github.push_release REPO_NAME, version, description, RELEASE_ASSETS unless ENV["DRY_RUN"]
end

desc "Get new release assets, update details and publish"
task :release do
  tag, notes = get_release

  update_readme tag
  update_release_notes tag
  update_pod tag

  commit_and_tag tag
  push_github_release tag, notes

  #this execs the process and must be called last
  push_pod
end


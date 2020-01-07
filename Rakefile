require 'pry'
require 'octokit'
require 'tmpdir'
require 'sdk/ci'

INTERNAL_REPO = "tenjin/ios-sdk"
INTERNAL_REPO_RELEASE_NOTES = "README.md"

RELEASE_NOTES = "RELEASE_NOTES.md"

def get_release
  @client = Octokit::Client.new(access_token: ENV["GITHUB_TOKEN"])

  release = @client.latest_release INTERNAL_REPO
  notes, version, assets = release[:body], release[:tag_name], release[:assets]

  assets.each do |a|
    f = @client.release_asset(a[:url], accept: "application/octet-stream")
    File.open(a[:name],"wb"){|file| file << f}
  end

  [version, assets, notes]
end

def update_pod(version)

end

def commit_and_tag(version)

end

def push_pod

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

desc "Get new release assets, update details and publish"
task :release do
  tag, assets, notes = get_release

  update_readme tag
  update_release_notes tag

  update_pod tag

  commit_and_tag tag

  push_pod()
end


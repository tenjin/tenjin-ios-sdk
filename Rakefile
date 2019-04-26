require 'octokit'
require 'tmpdir'

INTERNAL_REPO = "tenjin/ios-sdk"

desc "Get new release assets and publish"
task :release do
  
end

desc "Fetch internal assets for release"
task :get_github_release do
  client = Octokit::Client.new(access_token: ENV["GITHUB_TOKEN"])

  release = client.latest_release INTERNAL_REPO
  url, version, assets = release[:url], release[:tag_name], release[:assets]

  assets.each do |a|
    f = client.release_asset(a[:url], accept: "application/octet-stream")
    File.open(a[:name],"wb"){|file| file << f}
  end
end

desc "Update and push cocoapod reference"
task :update_pod do



end


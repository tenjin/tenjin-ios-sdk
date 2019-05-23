require 'pry'
require 'octokit'
require 'tmpdir'

INTERNAL_REPO = "tenjin/ios-sdk"

def get_release
  client = Octokit::Client.new(access_token: ENV["GITHUB_TOKEN"])

  release = client.latest_release INTERNAL_REPO
  assets.each do |a|
    f = client.release_asset(a[:url], accept: "application/octet-stream")
    File.open(a[:name],"wb"){|file| file << f}
  end

  [release[:tag_name], release[:assets], release[:body]]
end

desc "Get new release assets and publish"
task :release do
  version, assets, notes = get_release

  update_pod(version)
  push_pod()
end

desc "Fetch internal assets for release"
task :get_github_release do


end

desc "Update and push cocoapod reference"
task :update_pod do



end


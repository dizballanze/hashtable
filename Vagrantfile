Vagrant.configure(2) do |config|
  config.vm.box = "debian/jessie64"
  config.vm.synced_folder ".", "/home/vagrant/proj", type: "nfs"
  config.vm.network "private_network", ip: "10.1.1.66"
end

# vi:syntax=ruby
$script = <<SCRIPT
echo Provisioning started
sudo apt-get update
sudo apt-get install -y build-essential gdb valgrind
SCRIPT

Vagrant.configure(2) do |config|
  config.vm.box = "debian/jessie64"
  config.vm.synced_folder ".", "/home/vagrant/proj", type: "nfs"
  config.vm.network "private_network", ip: "10.1.1.66"
  config.vm.provision "shell", inline: $script
end

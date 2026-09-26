{
  description = "Midilord Zephyr development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    zephyr.url = "github:zephyrproject-rtos/zephyr/v4.4.0";
    zephyr.flake = false;

    zephyr-nix.url = "github:nix-community/zephyr-nix";
    zephyr-nix.inputs.nixpkgs.follows = "nixpkgs";
    zephyr-nix.inputs.zephyr.follows = "zephyr";
  };

  outputs = { nixpkgs, zephyr-nix, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      zephyrPackages = zephyr-nix.packages.${system};
      zephyrSdk = zephyrPackages.sdk.override {
        targets = [ "xtensa-espressif_esp32s3_zephyr-elf" ];
      };
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = [
          zephyrSdk
          zephyrPackages.pythonEnv
          pkgs.cmake
          pkgs.ninja
          pkgs.dtc
          pkgs.gperf
          pkgs.git
          pkgs.ccache
          pkgs.file
          pkgs.wget
          pkgs.which
        ];

        ZEPHYR_TOOLCHAIN_VARIANT = "zephyr";
      };
    };
}

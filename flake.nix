{
  description = "Pico 2 W Environment - Full SDK";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    
    pico-sdk-src = {
      url = "git+https://github.com/raspberrypi/pico-sdk?ref=master&submodules=1";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, pico-sdk-src }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          cmake
          gcc-arm-embedded
          python3
          picotool
        ];

        shellHook = ''
          export PICO_SDK_PATH="${pico-sdk-src}"
          export PICO_BOARD=pico2_w
          
          echo "🚀 Pico 2 W Environment Active (Full SDK with Submodules)"
        '';
      };
    };
}
{
  description = "My DWM Config";

  inputs.utils.url = github:numtide/flake-utils;
  inputs.utils.inputs.nixpkgs.follows = "nixpkgs";

  outputs = { self, nixpkgs, utils }: let
    inherit (utils.lib) eachDefaultSystemMap;
  in {
    packages = eachDefaultSystemMap ( system:
      let pkgsFor = import nixpkgs { inherit system; };
    in {
        ak-dwm = pkgsFor.stdenv.mkDerivation {
          pname = "ak-dwm";
          version = "0.0.1";
          src  = self;
          depsTargetTarget = with pkgsFor.xorg; [libX11 libXinerama libXft];
          prePatch = ''sed -i "s,/usr/local,$out," config.mk'';
        };
      default = self.packages.${system}.ak-dwm;
    } );
  };
}

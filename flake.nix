{
  description = "My DWM Config";

  inputs.utils.url = github:numtide/flake-utils;
  inputs.utils.inputs.nixpkgs.follows = "nixpkgs";

  outputs = { self, nixpkgs, utils }:
    let defaultSystemsMap = utils.lib.eachSystemMap utils.lib.defaultSystems;
    in {
      packages = defaultSystemsMap ( system:
        let pkgsFor = import nixpkgs { inherit system; };
        in rec {
          ak-dwm = pkgsFor.stdenv.mkDerivation {
            pname = "ak-dwm";
            version = "0.0.1";
            src  = self;
            depsTargetTarget = with pkgsFor.xorg; [
              libX11 libXinerama libXft
            ];
            prePatch = ''
              sed -i "s,/usr/local,$out," config.mk
            '';
          };
        default = ak-dwm;
      } );
    } // ( if ( ( builtins.compareVersions __nixVersion "2.7.0" ) <= 0 )
           then {
             defaultPackage =
               defaultSystemsMap ( system: self.packages.${system}.default );
           } else {} );
}

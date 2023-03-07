{
  description = "My DWM Config";

  outputs = { self, nixpkgs }: let

    eachDefaultSystemMap = fn: let
      defaultSystems = ["x86_64-linux" "aarch64-linux" "i686-linux"];
      proc           = name: { inherit name; value = fn name; };
    in builtins.listToAttrs ( map proc defaultSystems );

    overlays.ak-dwm = final: prev: {
      ak-dwm = final.stdenv.mkDerivation {
        pname            = "ak-dwm";
        version          = "0.0.1";
        src              = self;
        depsTargetTarget = [
          final.xorg.libX11
          final.xorg.libXinerama
          final.xorg.libXft
        ];
        prePatch = ''sed -i "s,/usr/local,$out," config.mk'';
      };
    };
    overlays.default = overlays.ak-dwm;

    nixosModules.ak-dwm.nixpkgs.overlays = [overlays.ak-dwm];
    nixosModules.default                 = nixosModules.ak-dwm;

    packages = eachDefaultSystemMap ( system: let
      pkgsFor = nixpkgs.legacyPackages.${system}.extend overlays.ak-dwm;
    in {
      inherit (pkgsFor) ak-dwm;
      default = pkgsFor.ak-dwm;
    } );  # End `packages'

    legacyPackages = eachDefaultSystemMap ( system: let
      pkgsFor = nixpkgs.legacyPackages.${system}.extend overlays.ak-dwm;
    in { inherit (pkgsFor) ak-dwm; } );

  in {

    inherit overlays nixosModules packages legacyPackages;

  };  # End `outputs'

}

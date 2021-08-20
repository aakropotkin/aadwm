{
  description = "Alex Ameen's DWM Config";

  inputs.nixpkgs.follows = "nix/nixpkgs";

  outputs = { self, nix, nixpkgs, ... }:
    let
      supportedSystems = [ "x86_64-linux" "i686-linux" "aarch64-linux" ];
      forAllSystems = f: nixpkgs.lib.genAttrs supportedSystems ( sys: f sys );
      version = "0.1.${nixpkgs.lib.substring 0 8 " +
                "self.lastModifiedDate}.${self.shortRev or "dirty"}";
    in {

      overlay = final: prev: {
        aa-dwm = with final;
          let
            nix = final.nix;
          in stdenv.mkDerivation {
            name = "aa-dwm";
            src  = self;

            depsTargetTarget = with pkgs.xorg; [ libX11 libXinerama libXft ];

            prePatch = ''
              sed -i "s@/usr/local@$out@" config.mk
            '';
          };
      };

      defaultPackage = forAllSystems ( sys: ( import nixpkgs {
        inherit sys;
        overlays = [ self.overlay nix.overlay ];
      } ).aa-dwm );

      nixosModule = { pkgs, ... }: {
        nixpkgs.overlays = [ self.overlay ];
      };

      nixosModules.aa-dwm = self.nixosModule;

    };
}

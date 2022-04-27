{
  description = "Alex Ameen's DWM Config";

  outputs = { self, nixpkgs, ... }:
    let
      supportedSystems = [ "x86_64-linux" "i686-linux" "aarch64-linux" ];
      forAllSystems = f: nixpkgs.lib.genAttrs supportedSystems ( sys: f sys );
      version = "0.1.${nixpkgs.lib.substring 0 8 " +
                "self.lastModifiedDate}.${self.shortRev or "dirty"}";
    in {
      packages = forAllSystems ( system:
        let
          pkgsFor = nixpkgs.legacyPackages.${system};
        in rec {
          aa-dwm = pkgsFor.stdenv.mkDerivation {
            name = "aa-dwm";
            src  = self;
            depsTargetTarget = with pkgsFor.xorg; [libX11 libXinerama libXft];
            prePatch = ''
              sed -i "s@/usr/local@$out@" config.mk
            '';
          };
        default = aa-dwm;
      } );
      defaultPackage =
        forAllSystems ( system: self.packages.${system}.default );
    };
}

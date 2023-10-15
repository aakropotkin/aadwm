# ============================================================================ #
#
#
#
# ---------------------------------------------------------------------------- #

{

# ---------------------------------------------------------------------------- #

  description = "My DWM Config";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs";


# ---------------------------------------------------------------------------- #

  outputs = { nixpkgs, ... }: let

# ---------------------------------------------------------------------------- #

    eachDefaultSystemMap = fn: let
      defaultSystems = ["x86_64-linux" "aarch64-linux" "i686-linux"];
      proc           = name: { inherit name; value = fn name; };
    in builtins.listToAttrs ( map proc defaultSystems );


# ---------------------------------------------------------------------------- #

    overlays.deps = final: prev: {};

    overlays.ak-dwm = final: prev: {
      ak-dwm = final.stdenv.mkDerivation {
        pname   = "ak-dwm";
        version = "0.0.1";
        src     = builtins.path {
          path   = ./.;
          filter = name: type: let
            bname = baseNameOf name;
            ext   = let
              m = builtins.match "[^.]+\\.(.*)" bname;
            in if m == null then bname else builtins.head m;
            ignoredFiles = [
              "flake.nix"
              "flake.lock"
              "dwm"
              "README"
              "LICENSE"
              "result"
              ".ccls-cache"
              "out"
            ];
            ignoredExts     = ["o" "so" "a" "tar" "tar.gz"];
            ignoredPatterns = ["result-.*" ".*~"];
            test            = patt: str: ( builtins.match patt str ) != null;
          in ! (
            ( builtins.elem bname ignoredFiles ) ||
            ( builtins.elem ext   ignoredExts ) ||
            ( builtins.any ( patt: test patt bname ) ignoredPatterns )
          );
        };
        depsTargetTarget = [
          final.xorg.libX11
          final.xorg.libXinerama
          final.xorg.libXft
        ];
        prePatch = ''sed -i "s,/usr/local,$out," config.mk'';
      };
    };

    overlays.default = nixpkgs.lib.composeExtensions overlays.deps
                                                     overlays.ak-dwm;


# ---------------------------------------------------------------------------- #

    nixosModules.ak-dwm.nixpkgs.overlays = [overlays.default];
    nixosModules.default                 = nixosModules.ak-dwm;


# ---------------------------------------------------------------------------- #

    packages = eachDefaultSystemMap ( system: let
      pkgsFor = nixpkgs.legacyPackages.${system}.extend overlays.ak-dwm;
    in {
      inherit (pkgsFor) ak-dwm;
      default = pkgsFor.ak-dwm;
    } );  # End `packages'


# ---------------------------------------------------------------------------- #

  in {

    inherit overlays nixosModules packages;

    legacyPackages = eachDefaultSystemMap ( system: let
      pkgsFor = nixpkgs.legacyPackages.${system}.extend overlays.ak-dwm;
    in { inherit (pkgsFor) ak-dwm; } );


  };  # End `outputs'


# ---------------------------------------------------------------------------- #

}

# ---------------------------------------------------------------------------- #
#
#
# ============================================================================ #

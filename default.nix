with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "physics-of-sounds";
  version = "0.1";

  src = ./.;

  buildInputs = [ fftw gnuplot makeWrapper ];

  patches = [ ./patch ];

  buildPhase = ''
    cd clean
    make all
  '';

  installPhase = ''
    mkdir -p $out/bin
    for binary in $(find * -executable -type f); do
      echo "hi"
      cp "$binary" $out/bin
    done
  '';

  postFixup = ''
    for script in "$out"/bin/*; do
      wrapProgram "$script" --prefix PATH : "$out/bin"
    done
  '';
}

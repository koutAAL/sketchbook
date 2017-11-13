/*
 * Circus_big_top.ino
 * Файл с примером использования библиотеки QBPlay
 * https://en.wikibooks.org/wiki/QBasic/Appendix#PLAY
 *
 * created 10.11.2017
 * modified 12.11.2017
 * with Arduino 1.8.3 (tested on Arduino Uno)
 *
 * Copyright 2017 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

#include "QBPlay.h"
QBPlay* play;
const byte speaker_pin = A3;

const char Circus_big_top[] PROGMEM = "MNT150L32O2EL4>EL16E.L32<E>E<E>E<EL4>EL16E.L32<E>E<E>E<E>EL16<D+DC+C<BA+AG+GF+FED+DC+L32>F+L4>F+L16F+.L32<F+>F+<F+>F+<F+L4>F+L16F+.L32<F+>F+<F+>F+<F+>F+L16<FED+DC+C<BA+AG+GF+FED+L32>GL4>GL16GL32O1B>F>G<F>G<FL4>GL16GL32O1B>F>G<F>GO1B>GFG+<B>AFA+<G>BF>CO1BO3C+<F>DO1GO3D+P32E<F>FP32F+O1BO3GP32G+O1GO3AP32BO1CO4C.P32O1GO3B.P32GA+P32BO1GO3A+P32AO1CO3G+.P32O1GO3G.P32GL16F+.L32O1GO3G.P32O1CO3A.P32O1GO3G+.P32GGP32G+O1GO3GP32F+O1CO3F.P32O1GO3E.P32GL16D+.L32O1GO3E.P32BG.P32O1GO3FP32FGL16C+.L32O1GO3D.P32BG.P32O1GO3FP32FGL16C+.L32O1GO3D.P32O1F>BP32>CO1EO3C+P32DO1DO3D+P32EO1CO3FP32F+BGP32G+AAP32BGL16A.L32BG.P32O1CO4C.P32O1GO3B.P32GA+P32BO1GO3A+P32AO1CO3G+.P32O1GO3G.P32GL16F+.L32O1GO3G.P32O1CO3A.P32O1GO3G+.P32GGP32G+O1GO3GP32F+O1CO3F.P32O1GO3E.P32GL16D+.L32O1GO3E.P32BD+.P32O1F+O3D+P32D+O1D+L16O3F+.L32O1F+>B.P32<EO3GP32AO1GO3GP32F+O1EL16O3E.L32O1GL16O3G.L32BL16B.L32O1BO3BO1BO3BO1BL16O3BP32L32O1BL16O3BP32L32O1BO3BO1A+O3BO1AO3BO1G+O3BO1GO3BO1F+O3BO1FO3BO1DP32CO4C.P32O1GO3B.P32GA+P32BO1GO3A+P32AO1CO3G+.P32O1GO3G.P32GL16F+.L32O1GO3G.P32O1CO3A.P32O1GO3G+.P32GGP32G+O1GO3GP32F+O1CO3F.P32O1GO3E.P32GL16D+.L32O1GO3E.P32BG.P32O1GO3FP32FGL16C+.L32O1GO3D.P32BG.P32O1GO3FP32FGL16C+.L32O1GO3D.P32O1F>BP32>CO1EO3C+P32DO1DO3D+P32EO1CO3FP32F+BGP32G+AAP32BGL16A.L32BG.P32O1CO4C.P32O1GO3B.P32GA+P32BO1GO3A+P32AO1CO3G+.P32O1GO3G.P32GL16F+.L32O1GO3G.P32O1CO3A.P32O1GO3G+.P32GGP32G+O1GO3GP32F+O1CO3F.P32O1GO3E.P32GL16D+.L32O1GO3E.P32O1DO3D.P32O1F+O3DP32DO1DL16O3A.L32O1F+O3D.P32O1C+O3D+.P32O1GO3D+P32D+O1C+L16O3A+.L32O1GP16DO3BP32>DO1GO4C+P32CO1DO3B.P32<C>A.P32O1BL16O3G.L32O1G>G<G>G<G>G<F>F<E>E<D>D<CL16>C.L32G>E<G>E<GL16>EL32O1G>GL16>E.L32O1CL16>C.L64<B>BL32>EO1C>C<C+>C+<D>DL64<D+>D+L32>EO1E>E<FL16>FL32GB>F<B>F<BL16>FL64O1E>EL32BL16>F.L32O1DL16>DL32G>DFDFDL16FL32<B>DL16F.L32O1AL16>A.L32>DFDFDL16FL32O1G>GL16>F.L32O1F>F<G>GL64<F>FL32>FO1E>E<D>D<E>EL64<F>FL32>FO1D>D<CL16>C.L32G>E<G>E<GL16>EL32<EGL16>E.L32GL16O1G.L32O3CECECL16EL32<G>CL16E.L32O1CL16>C.L32G>E<G>E<GL16EL32G<GL16O3E.L32O1CL16>C.L64B<BL32O3EO1C>C<D>D<E>EL64<F>FL32>EO1G>G<F+L16>F+.L32>CF+CF+CL16F+L32<A>CL16F+.L32O1CL16>CL32A>D+F+<A>F+O1BL16O3F+L32<ACL16>F+.L32O1EL16>E.L32>CGCGO1CL16>C.L32>EGEGO1DL16>D.L32>DGDGGL16O1G.L32O3FGFGO1CL16O3C.L32B<B<A>A<G>G<F>F<E>E<D>D<CL8>C.P32L32GL8<G.P32L32CL16>C.L32G>E<G>E<GL16>EL32O1G>GL16>E.L32O1CL16>C.L64<B>BL32>EO1C>C<C+>C+<D>DL64<D+>D+L32>EO1E>E<FL16>FL32GB>F<B>F<BL16>FL64O1F>FL32BL16>F.L32O1DL16>DL32G>DFDFDL16FL32<B>DL16F.L32O1AL16>A.L32>DFDFDL16FL32O1G>GL16>F.L32O1F>F<G>GL64<F>FL32>FO1E>E<D>D<E>EL64<F>FL32>FO1D>D<CL16>C.L32G>E<G>E<GL16>EL32<EGL16>E.L32GL16O1G.L32O3CECECL16EL32<G>CL16E.L32O1CL16>C.L32G>E<G>E<GL16EL32G<GL16O3E.L32O1CL16>C.L64B<BL32O3EO1C>C<D>D<E>EL64<F>FL32>EO1G>G<F+L16>F+.L32>CF+CF+CL16F+L32<A>CL16F+.L32O1CL16>CL32A>D+F+<A>F+O1BL16O3F+L32<ACL16>F+.L32O1EL16>E.L32>CGCGO1CL16>C.L32>EGEGO1DL16>D.L32>DGDGGL16O1G.L32O3FGFGO1CL16O3C.L32B<B<A>A<G>G<F>F<E>E<D>D<CL16>C.L32>E>C<E>C<EL8>CP8L16O1FL32A>CL8F.P16L16<E.P32DL32A>CL16F.P32L32<DP32CP32DP32EP32L16FL32A>CL4FL16<E.P32DL32A>CL16F.P32L32<DP32CP32DP32EFL16A.L32CL8F.P32L32CL16F.L32FL16A+.L32CL16F.L32FL16B.L32CL16F.L32FL16>C.L32<CL8A.P32L32CL16A.L32FL16>D.L32<CL16F.L32FL16>E.L32<CL16A.L32C+L16>F.L32<C+L8G+.P32L32C+L16G+.L32C+L16>D+.L32<C+L16G+.L32C+L16>C+.L32<C+L16G+.L32FL16>C.L32<CL8A.P32L32CL16A.L32FL16>C.L32<CL16A.L32FL16>C.L32<CL16A.L32A+L16>D.L32<FL8A+.P32L32FL16A+L32A+>DL16A+L32<FA+L16A+.L32>C+L16A+.L32<FL16A+L32C>CL16A.L32<FL8A.P32L32FL16AL32C>CL16G.L32<FL16AL32C>CL16F.L32<FL16AL32A+>DL16A.L32<FL8B.P32L32FL16BL32G>DL16G.L32<FL16BL32G>D+L16F+L32<F+GL16B.L32CL16>AL32<EGL16A+.L32CL16>GL32<EGL16A+.L32CL16>E.L32<GL16A+.L32CL16>DL32<GA+L16>C+L32FCL16A.L32<CL8F.P32L32CL16FL32FA+L16>A+.L32<CL16AL32FBL16>BL32<CFL16AL32F>CL16>C.L32O1CL8A.L32CFL16AL32F>DL16>D.L32O1CL16AL32F>EL16>EL32O1CFL16AL32C+>FL16>F.L32O1G+L8>C+.L32<FG+L16>C+L32<C+>GL16>G.L32O1FL16BL32C+>G+L16>G+L32O1FG+L16BL32C>AL16>A.L32O1FL8A.P32L32FL16AL32F>FL16>F.L32O1AL16>CL32<A>FL16>FL32O1FAL16>CL32BG+L16>G+.L32O1GL8>D.P32L32<GL16>DL32BGL16>G.L32O1F+L16>DL32BFL16>F.L32O1GL16>DL32<CO3DL16>D.L32O1AL16>CL32<CO3CL16>C.L32O1AL16>CL32<C>AL16>A.L32O1AL16>CL32<C>FL16>F.L32O1AL16>CL32<G>GL16>G.L32O1FL16BL32G>DL16>D.L32O1GL16BL32C>EL16>E.L32O1GL16>CL32<C>GL16>G.L32O1A+L16>CL32<F>FL16>F.L32O1AL8>C.L32<FAL16>CL32<FAL16>C.L32A>A<A>A<AL16>A.L32<AL16>A.L32AL16O1A.L32AABBC>C<C+>C+<D>D<D+>D+<E>E.P32<EL16>E.L32<C+L16>C+.L32AL16<A.L32FL16>F.L32<E>E<D>D<C+>C+<D>D<E>E<C+>C+AL16<A.L32B>C+L16<BL32AL8A.P32L32CL16>C.L32<C>C<C+>C+<D>D<E>E<F>F<F+>F+<G>G.P32<GL16>G.L32<EL16>E.L32<CL8>CL16A+.P32F+L32A.P64L16G.P32C.L32<A+L16>A+.L32<F+>F+<A>A<GL16>G.L32<CL16>C.L32C<CC+C+DDD+D+EEFFF+F+GGG+L16G+.L32AL16A.L32A+L16A+.L32BL16B.L32FL64O3CFL16AL32<CFCFCL16F.L32CL16F.L32FA+L16>A+L32<CL16F.L32FBL16>BL32<CL16F.L32FL64>FAL16>CL32O1A>F<A>F<AL16>F.L32<AL16>F.L32F>DL16>DL32O1AL16>F.L32F>EL16>EL32O1AL16>FL32C+<C+L64O3G+>C+L16FL32O1G+>C+<G+>C+<G+L16>C+.L32<G+L16>C+L32C+<C+O3D+L16>D+L32O1FL16>C+L32C+<C+O3C+L16>C+L32O1FL16>C+L32F<FL64O3FAL16>CL32O1A>F<A>F<AL16>F.L32<AL16>FL32F<FO3CL16>CL32O1AL16>FL32F<FO3CL16>CL32O1AL16>F.L32A+L64>FA+L16>DL32O1A+>D<A+>D<A+L16>DL32<FA+L16>D.L32A+>A+L16>A+L32O1FL16>D.L32A+>A+L16>A+L32O1FL16>C+L32C<CL64O4CFL16AL32O1F>C<F>C<FL16>CL32<FAL16>CL32C<CO3GL16>GL32O1FL16>CL32C<CO3FL16>FL32O1AL16>FL32C<CL64O4DFL16AL32O1G>F<G>F<GL16>FL32<GBL16>FL32G<GO3GL16>GL32O1BL16>FL32G<GO3F+L16>F+L32O1BL16>FL32C<CL64O4CEL16AL32O1A+L16>EL32C<CO3GL16>GL32O1A+L16>EL32C<CL64O3GA+L16>EL32O2CL16EL32C<CO3DL16>DL32O1A+O3C+L16>C+L32FL64<CFL16AL32O1A>F<A>F<AL16>FL32<A>CL16FL32F<F>A+L16>A+L32<CL16FL32F<F>BL16>BL32<CL16FL32F<FL64O3FAL16>CL32O1A>F<A>F<AL16>FL32<A>CL16FL32F<FO3DL16>DL32O1AL16>FL32F<FO3EL16>EL32O1AL16>FL32C+<C+L64O3G+>C+L16FL32O1G+>C+<G+>C+<G+L16>C+L32<G+>C+L16FL32C+<C+O3GL16>GL32O1BL16>FL32C+<C+O3G+L16>G+L32O1BL16>FL32C<CL64O4CFL16AL32O2CFCFCL16FL32<A>CL16F.L32A>FL16>FL32O1A>CL16FL32A>FL16>FL32O1A>CL16FL32G+L64>FBL16>FL32O1G+>F<G+>F<G+L16>FL32<G+BL16>FL32G+<G+O3EL16>EL32O1BL16>FL32B<BO3DL16>DL32O1BL16>FL32C<CL64O3FAL16>DL32O2CL16FL32C<CL64O3FAL16>CL32O2CL16FL32C<CO3AL16>FL32O1AL16>FL32C<CO3FL16AL32O1AL16>FL32C<CL64O3CAL16>CL32O2CFCFCL16FL32<A>CL16FL32C<CO3AL16>CL32O1GL16>EL32C<CO3GL16>CL32O1A+L16>EL32<F>C>FL16>FL64O2C+>EL32>E<G>GO2C>FL16>FL64O2D>EL32>E<G>GL64O1F>AL32>FL16>FP8L64O1F>CA>FL32>CL16FP8";

void setup(){
    play = new QBPlay(speaker_pin);
    play->start((__FlashStringHelper*) Circus_big_top);
}

void loop(){
    play->touch();
}
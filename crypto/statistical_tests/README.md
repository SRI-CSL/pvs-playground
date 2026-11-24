# SP 800-22 Rev. 1a

The input is a length and an array of bits, in generation order. Each test returns an applicability flag and a binary64 p-value. `accepts(result, alpha)` implements the significance comparison. Run each direction, state and template separately when recording results for multiple sequences. [SP 800-22 Rev. 1a, Chapters 2–4](https://csrc.nist.gov/pubs/sp/800/22/r1/upd1/final)

| Theory | Test entry points |
|---|---|
| [sts_counts](sts_counts.pvs) | Frequency, block frequency, runs, longest run of ones, 32×32 binary matrix rank, non-overlapping templates, overlapping templates, serial and approximate entropy |
| [sts_spectral](sts_spectral.pvs) | Discrete Fourier transform using Bluestein convolution and a radix-two FFT |
| [sts_complexity](sts_complexity.pvs) | Maurer's universal test and blockwise Berlekamp–Massey linear complexity |
| [sts_walk](sts_walk.pvs) | Forward and reverse cumulative sums, random excursions on ±1 through ±4 and the variant on ±1 through ±9 |
| [sts_suite](sts_suite.pvs) | Test imports, ten-bin p-value uniformity, pass proportion and theorem statements |

For the non-overlapping test, enumerate the integers below `2^m` for which `unbordered(pat,m,1)` holds. At width nine there are 148 templates. `overlapping` selects the published 9-bit, 1,032-bit-block profile. `overlapping_parameters` takes the all-ones template width, block length and final category. For the serial test, request both values of `second`. The library accepts bounded parameters, including widths through 30 for serial and 6 through 16 for Maurer. The spectral transform accepts lengths through 2³⁰ subject to available memory. Chapter 2 gives the sample sizes and parameter choices needed to interpret each statistic.

Run `python3 validation/check_assessments.py sts` from the catalogue root. The compressed fixture contains the first million bits of the NIST STS `data.pi`, packed most significant bit first. The test checks the million-point DFT, including the 475,280 coefficients below threshold, against the Appendix B p-value. It also checks prime and power-of-two transform lengths. The overlapping-template and linear-complexity checks use independently counted bins and the probabilities in §§2.8 and 2.10. These yield 0.2607037020 and 0.2468565662 for the π fixture. The worked 50-bit overlapping example is checked against the bitstring printed in §2.8.4. [NIST STS distribution and correction history](https://csrc.nist.gov/projects/random-bit-generation/documentation-and-software)

PVS2C represents binary64 values as 64-bit words. The shared attachments call system math and Boost.Math for distribution tails. Numerical accuracy and rounding depend on those libraries. The theorem statements and generated type-correctness conditions are open.

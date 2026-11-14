# Credits

The sources that shaped this project's setup - its standards, its tools and its workflow. Thank you to everyone
who published their work.

## For this game

- [AdventureT/OpenJPOG](https://github.com/AdventureT/OpenJPOG) and [Voikanaa/jpog-decomp](https://github.com/Voikanaa/jpog-decomp) - other work on Jurassic Park: Operation Genesis and the Toshi engine, with different approaches.

## Standards and method

- [zeldaret/tp](https://github.com/zeldaret/tp), [zeldaret/mm](https://github.com/zeldaret/mm), [zeldaret/oot](https://github.com/zeldaret/oot), [n64decomp/sm64](https://github.com/n64decomp/sm64) - the readability standard was first calibrated against these: honest placeholders are normal, invented code is not. Also zeldaret mm's CONTRIBUTING and REVIEWING guides.
- [homm3-decomp](https://github.com/sushi-shi/homm3-decomp) - the PC calibration (same compiler as Zoo Tycoon): its agent rules and audits gave us the rules on raw offset arithmetic, steering pragmas and constructs, gotos, and "names can change bytes".
- [fnv_decomp](https://github.com/momusdigital/fnv_decomp) - name source tags; also our counter-example for what tricks look like at scale.
- [tomb3](https://github.com/Trxyebeep/tomb3), [TOMB4](https://github.com/Trxyebeep/TOMB4), [TOMB5](https://github.com/Trxyebeep/TOMB5), [SpaceCadetPinball](https://github.com/k4zmu2a/SpaceCadetPinball), [cdcEngineDXHR](https://github.com/rrika/cdcEngineDXHR) - PC source read to correct checks that were too strict.
- [lemiur: Game-Decompilation-Skill-For-Claude](https://github.com/lemiur/Game-Decompilation-Skill-For-Claude) - the fakematch rules and the order for classifying why a function does not match.
- [momo5502: Letting AI agents decompile a game](https://momo5502.com/posts/2026-10-09-game-decompilation/) - re-reading the rules every round, keeping context small, the independent checker.
- [doldecomp/melee FAQ](https://github.com/doldecomp/melee/wiki/FAQ), [isledecomp](https://github.com/isledecomp/isle) CONTRIBUTING, [Decomp Academy](https://decomp-academy.dev), [Chris Lewis: Using coding agents to decompile N64 games](https://blog.chrislewis.au/using-coding-agents-to-decompile-nintendo-64-games/).
- Buse & Weimer, [Learning a metric for code readability](https://web.eecs.umich.edu/%7Eweimerw/p/weimer-tse2010-readability-preprint.pdf).

## Tools and ideas

- [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) (Simon Lindholm), [decomp.wtf](https://github.com/i12bp8/decomp.wtf) (Sam Wolfs) and [decompdecomp](https://github.com/n-delic/decompdecomp) - the idea and rewrite list behind `Tools/permuter`, look-alike search, batching small functions, the per-function retry limit.
- [awesome-rea](https://github.com/yibie/awesome-rea), [Retro Reversing: AI-assisted decompilation](https://www.retroreversing.com/ai-assisted-decompilation), [GAMBIconf: Starting a decompilation project from zero](https://gambiconf.substack.com/p/starting-a-decompilation-project), [the 500-billion-token harness write-up](https://www.developersdigest.tech/blog/agent-harness-pass-fail-oracle-500b-token-decompile-2026) - surveys and lessons: a checker the agents cannot edit, deliberately wrong candidates, mechanical tools before prompts.
- [Ghidra](https://ghidra-sre.org) (NSA) for the first-pass decompilation, [Capstone](https://www.capstone-engine.org) for disassembly in the comparison tools, [llama.cpp](https://github.com/ggml-org/llama.cpp) / [Ollama](https://ollama.com) and Qwen 3.5 (Alibaba) for the optional local reader (`Tools/localai`).
- [github/choosealicense.com](https://github.com/github/choosealicense.com) for the CC0 1.0 text.

## Assistance

Reconstruction, tooling and notes were produced with Claude (Anthropic) as an assistant, under the rules in
`CLAUDE.md`; every result is verified by an independent checker and reviewed by the project's author.

Names and links are given as credit and for reference. None of these projects is affiliated with this one or
endorses it, and no code was copied from them into `Src/`.

I would like to give a big thanks to bwrsandman for finding Intel C++ Compiler Version 5.0.1 Build 010525Z. I wouldn't have been able to get this project off the ground without him finding the compiler I'm using. It isn't 020125Z unfortunately (the compiler build Jurassic Park Operation Genesis was built with), but so far I have a good match rate. So long as I'm unable to find build 020125Z I won't be able to match all functions, but I can get pretty close. OpenToshi, OpenJPOG, and OpenBarnyard were also used as reference materials.

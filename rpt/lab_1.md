1.Spike model and co-sim. 

a.Spike model (with risc-v pk) execution correctness: simulate programs atop the proxy kernel
<img width="623" alt="1666523144608" src="https://user-images.githubusercontent.com/59349853/197389778-f83d9899-0da2-4dde-a664-aecfb563e0b2.png">

<img width="378" alt="1666533837821" src="https://user-images.githubusercontent.com/59349853/197725707-6cc65ce8-df84-4cf7-a12b-008de97a5ea7.png">
b.GreenRio core RTL execution correctness: pass some ISA tests (Synopsys VCS environment)
<img width="637" alt="1666343708007" src="https://user-images.githubusercontent.com/59349853/197389763-9041b30a-5819-4ea0-8f36-18376968a7d5.png">
<img width="639" alt="1666343751670" src="https://user-images.githubusercontent.com/59349853/197389795-1a07ac0f-86ec-4980-8afa-8fb999ce4ad8.png">
<img width="639" alt="1666343751671" src="https://user-images.githubusercontent.com/59349853/198014151-153ce7cd-8b2d-4c05-aa2d-f94be0db3633.png"

c.Spike model + GreenRio RTL co-simulation system. 

i.You need to run the elf file on the spike emulator and print the log
<img width="576" alt="1666686441826" src="https://user-images.githubusercontent.com/59349853/197726011-30670541-366d-45fe-8edf-82fa1e8f22c4.png">. 

ii.You need to have GreenRio run the risc-v elf in an RTL simulation environment and get the corresponding results: register states, values, etc. 

<img width="490" alt="1666686820669" src="https://user-images.githubusercontent.com/59349853/197726051-bccb225e-63ba-4d18-bbab-e4411b1401c2.png">

![截屏2022-12-12 16 15 50](https://user-images.githubusercontent.com/59349853/206995777-594d382e-9892-405b-8b5e-20bcdf06f2af.png)

2.Open EDA flow. 
a.GreenRio core logic synthesis by yosys (use 2 libs as different conrer)   
<img width="490" alt="1666686820669" src="https://user-images.githubusercontent.com/59349853/198014979-e39b5746-b1a1-49f3-910e-39e4aaccd07c.png">

<img width="490" alt="1666686820669" src="https://user-images.githubusercontent.com/59349853/198014990-49e89d20-b921-4607-9d97-118a19cd6eab.png">


See riosclass_template/openlane for synthesis documents.

b.GreenRio core gate level netlist + Spike co-sim execution correctness  
See riosclass_template/openlane/hehe.v for gate level netlist documents.

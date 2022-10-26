1.Spike model and co-sim. 

a.Spike model (with risc-v pk) execution correctness: simulate programs atop the proxy kernel
<img width="623" alt="1666523144608" src="https://user-images.githubusercontent.com/59349853/197389778-f83d9899-0da2-4dde-a664-aecfb563e0b2.png">

<img width="378" alt="1666533837821" src="https://user-images.githubusercontent.com/59349853/197725707-6cc65ce8-df84-4cf7-a12b-008de97a5ea7.png">
b.GreenRio core RTL execution correctness: pass some ISA tests (Synopsys VCS environment)
<img width="637" alt="1666343708007" src="https://user-images.githubusercontent.com/59349853/197389763-9041b30a-5819-4ea0-8f36-18376968a7d5.png">
<img width="639" alt="1666343751670" src="https://user-images.githubusercontent.com/59349853/197389795-1a07ac0f-86ec-4980-8afa-8fb999ce4ad8.png">
<img width="625" alt="1666343856640" src="https://user-images.githubusercontent.com/59349853/197389817-31f9b1af-5493-42e4-9e9a-b28afb52b2f8.png">
c.Spike model + GreenRio RTL co-simulation system. 

i.You need to run the elf file on the spike emulator and print the log
<img width="576" alt="1666686441826" src="https://user-images.githubusercontent.com/59349853/197726011-30670541-366d-45fe-8edf-82fa1e8f22c4.png">. 

ii.You need to have GreenRio run the risc-v elf in an RTL simulation environment and get the corresponding results: register states, values, etc. 

<img width="490" alt="1666686820669" src="https://user-images.githubusercontent.com/59349853/197726051-bccb225e-63ba-4d18-bbab-e4411b1401c2.png">

2.Open EDA flow. 
a.GreenRio core logic synthesis by yosys (use 2 libs as different conrer)   

<img width="544" alt="1666535407668" src="https://user-images.githubusercontent.com/59349853/197725915-1a169ddb-9c76-4e05-88f7-d79b336d235b.png">

<img width="603" alt="1666451014523" src="https://user-images.githubusercontent.com/59349853/197389872-68a8355f-eb60-442e-885c-57eca490fa4f.png">
<img width="604" alt="1666535559251" src="https://user-images.githubusercontent.com/59349853/197725941-6b20ff90-cfcd-4af3-a33d-9fa9c90135db.png">
<img width="627" alt="1666535621490" src="https://user-images.githubusercontent.com/59349853/197725966-5b1094fc-4f14-418b-8e08-cdca0eafaae4.png">

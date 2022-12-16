1.C model for original GreenRio frontend  
See code in rioclass_template/cmodel.  
```
    memory=LoadHex(hex_path)
    processor=new Processor;
    bus=new Bus;
    Simulation sim;
    sim.SetBus(bus);
    sim.SetMemory(memory);
    sim.SetProcessor(processor);
    sim.Init();
    for(int i=0;i<maxCycle;i++){
        sim.Tick();
    }
```  

 
First, load hex files to memory.  
In fetch stage, Instructions are fetched from Icache and pushed into a FIFO queue.  
In decode stage, it pulls instructions out of the instruction buffer and generates the appropriate micro-op to place into the pipeline.  


2.C frontend model(original), performance similarity of C model & RTL must within 20%, the less the better


3.GreenRio pipeline performance improvement: frontend - 25%  

(based on 1.a) C frontend model (improved) - 15%  

(based on 2.a) RTL implementation, performance similarity of C model & RTL must within 20%, or the C model would be invalid - 10%  


4.Open EDA flow - 40%
(based on 2.b) GreenRio core(improved) RTL synthesis - 0%  

Synthesis report is put in riosclass_template/openlane/RUN_2022.12.13_00.09.56/logs/synthesis/1-synthesis.log

```
[STEP 1]
[INFO]: Running Synthesis (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/synthesis/1-synthesis.log)...
[STEP 2]
[INFO]: Running Single-Corner Static Timing Analysis (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/synthesis/2-sta.log)...
[INFO]: Creating a netlist with power/ground pins.
[STEP 3]
[INFO]: Running Initial Floorplanning (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/floorplan/3-initial_fp.log)...
[INFO]: Extracting core dimensions...
[INFO]: Set CORE_WIDTH to 1908.54, CORE_HEIGHT to 1895.84.
[STEP 4]
[INFO]: Running IO Placement...
[STEP 5]
[INFO]: Running Tap/Decap Insertion (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/floorplan/5-tap.log)...
[INFO]: Power planning with power {vccd1} and ground {vssd1}...
[STEP 6]
[INFO]: Generating PDN (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/floorplan/6-pdn.log)...
[STEP 7]
[INFO]: Running Global Placement (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/placement/7-global.log)...
[INFO]: Skipping Placement Resizer Design Optimizations.
[STEP 8]
[INFO]: Running Detailed Placement (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/placement/8-detailed.log)...
[INFO]: Skipping Placement Resizer Timing Optimizations.
[STEP 9]
[INFO]: Running Global Routing Resizer Timing Optimizations (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/routing/9-resizer.log)...
[STEP 10]
[INFO]: Running Detailed Placement (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/routing/10-diode_legalization.log)...
[STEP 11]
[INFO]: Running Global Routing (log: designs/hehe/runs/RUN_2022.12.13_00.09.56/logs/routing/11-global.log)...
[INFO]: Starting OpenROAD Antenna Repair Iterations...
[INFO]: Starting antenna repair iteration 1 with 189 violations...
[INFO]: [Iteration 1] Failed to reduce antenna violations (189 -> 189), stopping iterations...
```

(based on 3.a) GreenRio core(improved) floorplanning, placement and CTS- 20%

Floorplanning report is put in riosclass_template/openlane/RUN_2022.12.13_00.09.56/logs/floorplan

Placement report is put in riosclass_template/openlane/RUN_2022.12.13_00.09.56/logs/placement  

CTS report is put in riosclass_template/openlane/RUN_2022.12.13_00.09.56/logs/cts

(based on 3.b) GreenRio core(improved) global routing - 20%  

Global routing report is put in riosclass_template/openlane/RUN_2022.12.13_00.09.56/logs/routing




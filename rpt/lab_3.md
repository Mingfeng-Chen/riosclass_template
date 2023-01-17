1.GreenRio microarchitecture performance improvement - 50%  

a.Finishing your Greenrio performance model (frontend, backend, and uncore part) - 25%  

1. You need to complete the backend model - 5%  

   Backend codes are put in cmodel/pipeline .

2. You need to complete the uncore model: L1 data cache, instruction cache, and memory interface - 15%  

   Uncore codes are put in cmodel/cache .

3. Your model needs to be verified by passing some ISA test or benchmarks - 5%  

   Searching for original Greenrio performance issues/bugs by comparing against the model, the more the better - 10%   

b.Searching for original Greenrio performance issues/bugs by comparing against the model, the more the better - 10%  

i.Find out the improvement points of the core part: such as fetch, rob, lsu, or buffer design. Please find at least one place that can be improved and explain the reason for your modification. - 5%  

The fetch stage can appropriately increase the number of instructions fetched each time, and then decide whether to discard the partially fetched instructions according to whether to jump.  

ii.Find out the improvement points of the uncore part. For example, change the blocking design to a non-blocking design. Please find at least one place that can be improved and explain the reason for your modification. - 10%  

For cache, it can increase the length of the cache line, make the number of instructions stored more, and facilitate the design of superscalar processors.  

2.EDA flow - 40%  

a.Greenrio core RTL to GDS flow by openlane- 40%  

i.GDS generation - 10%  

The log of GDS is put in openlane/lab_3/logs/signoff .  

ii.Signoff report generation: your flow should pass DRC/LVS check - 15%  

i.In the lab report, briefly describe what DRC is; the DRC problems you have encountered (If you have not encountered such a problem, please skip it), and the common solutions. - 5%  

Design Rule Checking (DRC) verifies as to whether a specific design meets the constraints imposed by the process technology to be used for its manufacturing. DRC checking is an essential part of the physical design flow and ensures the design meets manufacturing requirements and will not result in a chip failure. The process technology rules are provided by process engineers and/or fabrication facility.  

ii.In the lab report, briefly describe what LVS is; the LVS problems you have encountered (If you have not encountered such a problem, please skip it), and the common solutions. - 5%  

The Layout Versus Schematic (LVS) is the class of electronic design automation (EDA) verification software that determines whether a particular integrated circuit layout corresponds to the original schematic or circuit diagram of the design.  

3.Lab report - 10%  

a.Lab report and Presentation- 10%  



 


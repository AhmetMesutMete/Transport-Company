# Transport-Company
Simulation Techniques

Task:
- Simulate a transport company, where k trucks with capacity of u units transport cargo goods between the headquarters and n regional depots.
- Goods arrive in batches of size r units, where r is a random variable following normal distribution with mean μ𝑟 and variance σr2 (but the lowest possible size is 0.1 unit and the highest is 10 units).
- In the headquarters the cargo batch destination depot 𝑑𝑛 is a random variable following uniform distribution with equal probability for each depot, while the cargo batch destination for all cargo generated in depots is the headquarters.
- The time interval between the arrival (generation) of two consecutive cargo batches is a random variable with exponential distribution and average 𝑐ℎ𝑞 and 𝑐𝑑 for the headquarters and each depot, respectively.
- Cargo batches wait in queues at the headquarters and the depots until they are taken by the next truck going to the destination point of a cargo batch, where the truck destination at the headquarters is selected with strategy S, while for the depots the destination is always the headquarters.
- After the destination is determined the cargo batches destined to this point are loaded in first-in first-out order (FIFO) until the next one exceeds the truck capacity.
- Only full batch can be loaded, assuming there is enough space in the truck.
- In the headquarters there are M loading/unloading platforms, while in each depot there are N loading/unloading platforms, with single platform able to accommodate one truck.
- Trucks upon arrival enter a free platform unless all of them are occupied – in such a case they wait in queue. Then they are unloaded and later loaded, with the loading and unloading time for each cargo batch determined as r*𝑇𝐼 and r*𝑇𝑢, respectively.
- Delivered cargo batches leave the system. Trucks leave the platform according to strategy P.
- The traveling time for each truck between any depot and headquarters follows normal distribution with average μ𝑡 and variance σt2.

Simulation Parameters:





![image](https://user-images.githubusercontent.com/69396993/197343439-887818b1-6792-4819-9509-8e6f4dfdaea9.png)

Strategies used in the Project:



![image](https://user-images.githubusercontent.com/69396993/197343514-5bd74ab6-b2d8-48d1-819d-3e43a7760a03.png)

Method used in the Project:



![image](https://user-images.githubusercontent.com/69396993/197343549-5bad0004-9850-438e-af22-3a63e5ac4efc.png)

Simulation Model Scheme:

Please find the simulation scheme I prepared below. I believe that it will help you to picture how events will be carried out in your mind and will give you a chance to understand the process better.



![image](https://user-images.githubusercontent.com/69396993/197343592-01d32e93-2d41-44d9-a91d-7f3a93e95c0f.png)

Randomly selected starting variables:



![image](https://user-images.githubusercontent.com/69396993/197343970-27ceb8c5-70f7-4906-9e00-7754ac6f8b18.png)


Result:



![image](https://user-images.githubusercontent.com/69396993/197344530-2f8d131f-886c-409a-9e9a-6c588e5f29a1.png)


It took a long time to obtain consistent results and ensure that the system was functioning properly. However, as a result of this project, I received a decent grade. You can write your own code by studying how this code's algorithms and strategies are implemented. Best wishes. Ahmet Mesut

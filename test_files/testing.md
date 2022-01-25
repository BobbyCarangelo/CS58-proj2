## Bridge Simulation Testing

To test that the bridge simulation is properly tested I wrote the test inputs found in this directory. To run one of the scenarios, copy that test file's content into ../sim_input and run "main f". See below for each tests' description and expected output.

### test_1

Test 1 displays that bad interleavings - ie cars going in opposite directions - do not occur because two cars get on the bridge going towards hanover even though a car was prompted to get on going towards norwich in between, but waits until both are off. When the second car gets on towards hanover, there is one car in the queue going to norwich, as can be seen in test_1_output.

### test_2

Test 2 displays that bad interleavings - ie more than 3 cars getting on the bridge - do not occur. In this simulation five cars are prompted to get on going to hanover but there are never more than 3 on the bridge at a time. Also, this simulation shows efficiency because as soon as a car gets off a new one gets on, which is why for the fourth and fifth cars there are 3 cars on the bridge. See test_2_output

### test_3

Test 3 shows liveness because it prooves that cars eventually get off the bridge. For this reason, when the second car going towards norwich is gets on the bridge the bridge only has one car because the first one crossed. This was invoked by delaying the second car from getting on the bridge with a sleep. See output in test_3_output

### test_4 and test_5

Tests 4 and 5 show that bad interleavings are not present in a larger scale simulation. Outputs were not explicitly captured because it did not fit in one terminal window capture


# Hesteretic optimization for the Sherrington-Kirkpatrick spin glass

## 1. Two classical Ising spin glass models

The Hamiltonian is given by
$$
E = - 1/2  \sum_{i, j}^{N}  J_{ij}  \sigma_i * \sigma_j - H \sum_{i}^{N} \xi_i * \sigma_i
$$
The first term is the energy of the spin glass without the external field. The second term is the external demagnetizing field applied to minumize the energy. ki is the random direction of the field at each site i.

The aim of the optimization problem is to find the spin values $$$\sigma = \pm1$$$ that minimize ther first term.

### 1.1 Sherrington-Kirkpatrick Ising spin glass

In SK model, each spin interact with all the others

    - Jij = zij/sqrt(N),
        where zij is a random Gaussian number with zero mean and unit variance.
    - ki = +/- 1,
        which is the direction of H randomly changed from site to site.

### 1.2 Edwards-Anderson Ising spin glass

In EA model, each spin only interact with the nearest-neighbor couplings.

    - Jij = zij, only for the nearest neighbor,
    - ki = =/- 1.
    
## 2. ACD and HO algorithm
--------------------------------------------------------------------------

### 2.1 AC demagnetization (ACD) algorithm

* Basic ideas of quenching the system: *

    a. Staring from a random initial state {si},
    b. Indetify all unstable spins opposite the local fields:
        hi = \sum_{j} * Jij * si + H * ki,
    c. Flip randomly one of them and update the local fields,
    d. Repeat a and b until all spins are stable
    
* ACD process: *

    1. Start with an external field H = max{-ki*\sum_j*Jij*ki}, and a configuration si = ki,
    2. Quench the system as described above until no spin is unstable,
    3. Check the energy, and save the corresponding configuration,
    4. Decrease the field to -g*H, where 0.8 < g < 1.0 usually,
    5. Repeat 2-3-4 until the field is so small that there is no futher flip.
    6. Compare the final energy with the previous saved energy, choose the smallest one.
    
### 2.2 Hysteretic optimization

* Advantages and disadvantages of ACD *

Runs 3-10 times faster than simulated annealing so that could be applied to larger system. However, the final state is definitely above the groud state.

* Shakeup the system *

In order to approach the groud state futher, we start from the configuration obtained via ACD, but with a slightly smaller H and differet {ki}, and then apply ACD algorithm to the new system again.

    1. Start from a new H, and new {ki},
    2. Optimizate the system via ACD algorithm,
    3. Repeat 1-2 again and again until reach a stopping conditions.

We call this combination of ACD and shakeups as the hysteretic optimization.

* Stopping conditions *

    1. Shakeup ns_N times for the system with the same size N.
        Simplest but hard to find the optimal ns_N in advance, and takes the same steps for both the easiest and the hardest problem.
    
    2. Stop when the results keeps almost the same after several shakeups.
    
The reliability need to be checked. 




    
    
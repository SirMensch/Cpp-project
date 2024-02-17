This is a simulation of the Inverse Pendulum.

$`\phi`$ and $`x`$ are the variables for the angle of the stick (also called pole) and the position of the platform in the horizontal.

$`\phi`$ is defined as 0, when the pole stands up and the positive direction is defined clock-wise.

$`x`$ is defined positive to the right. $`l`$ is the length of the stick.

The position of the stick $`x_s`$ is defined by $`x_s = x +  \frac{l}{2} \sin \phi`$ and the y-component by $`y_s = y + \frac{l}{2} \cos \phi`$

Since $`y`$ is constant. The resulting velocities can be derived by $`\dot{x}_s = \dot{x} + \frac{l}{2} \dot{\phi} \cos \phi`$ 
and $`y_s = - \frac{l}{2} \dot{\phi} \sin \phi`$

The energy of the system is given by:

$$E_{ges} = E_{kin} + E_{pot}$$.

$$E_{kin} = E_{trans,p} + E_{rot,p} + E_{trans,s} + E_{rot,s} = \frac{1}{2} m_p \dot{x}^2 + 0 + \frac{1}{2} m_s (\dot{x}_s^2 + \dot{y}_s^2) + \frac{1}{2} I_s \dot{\phi}^2$$

where:

$$\dot{x}_s^2 + \dot{y}_s^2 = \frac{l^2}{4} \dot \phi^2 \sin^2 \phi + \dot{x}^2 + 2 \dot{x} \frac{l}{2} \dot{\phi} \cos \phi + \frac{l^2}{4} \dot \phi^2 \cos^2 \phi 
= \dot{x}^2 + \frac{l^2}{4} \dot \phi^2 + \dot{x} l \dot{\phi} \cos \phi$$

Enter this equation into the $`E_{kin}`$:

$$E_{kin} =\frac{1}{2} (m_p + m_s) \dot{x}^2 + \frac{1}{2} (I_s + \frac{l^2}{4} m_s) \dot{\phi}^2 + \frac{1}{2} m_s \dot{x} l \dot{\phi} \cos \phi$$

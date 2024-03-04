This is a simulation of the Inverse Pendulum.

# Energy Equation

$`\phi`$ and $`x`$ are the variables for the angle of the stick (also called pole) and the position of the platform in the horizontal.

$`\phi`$ is defined as 0, when the pole stands up and the positive direction is defined clock-wise.

$`x`$ is defined positive to the right. $`l`$ is the length of the stick.

The position of the stick $`x_s`$ is defined by $`x_s = x +  \frac{l}{2} \sin \phi`$ and the y-component by $`y_s = y + \frac{l}{2} \cos \phi`$

Since $`y`$ is constant. The resulting velocities can be derived by $`\dot{x}_s = \dot{x} + \frac{l}{2} \dot{\phi} \cos \phi`$ 
and $`y_s = - \frac{l}{2} \dot{\phi} \sin \phi`$

The energy of the system is given by:

$$E_{tot} = E_{kin} + E_{pot}$$.

$$E_{kin} = E_{trans,p} + E_{rot,p} + E_{trans,s} + E_{rot,s} = \frac{1}{2} m_p \dot{x}^2 + 0 + \frac{1}{2} m_s (\dot{x}_s^2 + \dot{y}_s^2) + \frac{1}{2} I_s \dot{\phi}^2$$

where:

$$\dot{x}_s^2 + \dot{y}_s^2 = \frac{l^2}{4} \dot \phi^2 \sin^2 \phi + \dot{x}^2 + 2 \dot{x} \frac{l}{2} \dot{\phi} \cos \phi + \frac{l^2}{4} \dot \phi^2 \cos^2 \phi 
= \dot{x}^2 + \frac{l^2}{4} \dot \phi^2 + \dot{x} l \dot{\phi} \cos \phi$$

Enter this equation into the $`E_{kin}`$:

$$E_{kin} =\frac{1}{2} (m_p + m_s) \dot{x}^2 + \frac{1}{2} (I_s + \frac{l^2}{4} m_s) \dot{\phi}^2 + \frac{1}{2} m_s \dot{x} l \dot{\phi} \cos \phi$$

We can calculate the moment of intertia $`I_s`$ for a stick by:

$$I_s = \frac{1}{12} m_s l^2$$

and the $`E_{pot}`$ by:

$$E_{pot} = m_s g \frac{l}{2} \cos \phi $$

So the total energy $`E_{tot}`$ is given by:

$$E_{tot} = m_s g \frac{l}{2} \cos \phi + \frac{1}{2} (m_p + m_s) \dot{x}^2 + \frac{1}{6} m_s l^2 \dot{\phi}^2 + \frac{1}{2} m_s \dot{x} l \dot{\phi} \cos \phi$$

# System Equation

We use the Lagrangian formula:

$`\frac{d}{dt} \frac{\delta L}{\delta \dot{q_i}} - \frac{\delta L}{\delta q_i} = 0`$ where $`L = E_{kin} - E_{pot}`$

For $`q_i = x`$ we get:

$$(m_p + m_s) \ddot{x} + \frac{1}{2} m_s l ( \ddot \phi \cos \phi - \dot \phi^2 \sin \phi) = 0$$

$$ (m_p + m_s) \ddot{x} = \frac{1}{2} m_s l (\dot \phi^2 \sin \phi - \ddot \phi \cos \phi) $$

For $`q_i = \phi`$ we get:

$$ \frac{1}{3} m_s l^2 \ddot \phi + \frac{1}{2} m_s l (\ddot{x} \cos \phi - \dot{x} \dot \phi \sin \phi) + \frac{1}{2} m_s l \dot x \dot \phi \sin \phi - m_s g \frac{l}{2} \sin \phi = 0$$

$$\frac{l}{3} \ddot \phi + \frac{1}{2} \ddot{x} \cos \phi - \frac{g}{2} \sin \phi = 0$$

For our system we add friction in $`x`$ and $`phi`$:

$` (m_p + m_s) \ddot{x} = \frac{1}{2} m_s l (\dot \phi^2 \sin \phi - \ddot \phi \cos \phi) - b_p \dot x`$ where $`b_p = \mu_{trans} g m_p`$

$`\frac{l}{3} \ddot \phi + \frac{1}{2} \ddot{x} \cos \phi - \frac{g}{2} \sin \phi = - \frac{b_s}{m_s l} \dot \phi`$ where $`b_s = \mu_{rot} g m_s`$

Final equations are:

$$\ddot{x} = \frac{1}{m_p + m_s} \big( \frac{1}{2} m_s l (\dot \phi^2 \sin \phi - \ddot \phi \cos \phi) - b_p \dot x \big)$$

$$\ddot \phi = \frac{3}{l} \big( \frac{1}{2}(g \sin \phi -  \ddot{x} \cos \phi)  - \frac{b_s}{m_s l} \dot \phi \big)$$

Now we derive the transfer functions for the linearized system around $`x = 400`$ and $`\phi = 0`$. 

The friction of the stick can be ignored, because we don't want high angular velocities $`\frac{b_s}{m_s l} \dot \phi = 0`$:

$$ (m_p + m_s) \ddot{x} = - \frac{1}{2} m_s l \ddot \phi - b_p \dot x + F(s)$$

$$\frac{l}{3} \ddot \phi + \frac{1}{2} \ddot{x} - \frac{g}{2} \phi = 0$$

Now we split $`x`$ and $`\phi`$:

$$ \Phi(s) = - \frac{1}{2} \frac{s^2}{\frac{l}{3} s^2 - \frac{g}{2}} X(s)$$

Then we insert this equation into the other one:

$$\big( (m_p + m_s) s^2 + b_p s \big) X(s) + \frac{1}{2} m_s l s^2 \Phi(s) = F(s)$$

$$\big( (m_p + m_s) s^2 + b_p s \big) X(s) - \frac{1}{4} m_s l s^2 \frac{s^2}{\frac{l}{3} s^2 - \frac{g}{2}} X(s) = F(s)$$

$$ (\frac{l}{3} s^2 - \frac{g}{2}) \big( (m_p + m_s) s^2 + b_p s \big) X(s) - \frac{1}{4} m_s l s^4 X(s) = (\frac{l}{3} s^2 - \frac{g}{2}) F(s)$$

$$(\frac{l(m_p+\frac{m_s}{4})}{3}s^4 + \frac{l}{3} b_p s^3 - \frac{g}{2}(m_p + m_s) s^2 - \frac{g}{2} b_p s) X(s) = (\frac{l}{3} s^2 - \frac{g}{2}) F(s)$$

$$\frac{X(s)}{F(s)} = \frac{l s^2 - \frac{3g}{2}}{l(m_p+\frac{m_s}{4})s^4 + b_p s^3 - \frac{3g}{2}(m_p + m_s) s^2 - \frac{3g}{2} b_p s}$$

For $`P_s(s)`$, we insert this equation:

$$\frac{\Phi(s)}{F(s)} = \frac{-\frac{3}{2}s}{l(m_p+\frac{m_s}{4})s^3 + b_p s^2 - \frac{3g}{2}(m_p + m_s) s^1 - \frac{3g}{2} b_p}$$

# PID

The formula for our PID looks like this:

$$ \frac{F(s)}{\phi(s)} = K_c + \frac{K_i}{s} + K_d s$$

When we our zeros to $`z = [-3, -4]`$ and our pole to $`p = 0`$, then we get by using Matlab we get:

$$K_c = 210, K_i = 360, K_d = 30$$

Caution: $`x`$ is not stable with this controller.

# PQL

For the PQL we transform our model to a state-space model.

$$ (m_p + m_s) \ddot{x} = - \frac{1}{2} m_s l \ddot \phi - b_p \dot x + F(s)$$

$$\ddot \phi = - \frac{3}{2l} \ddot{x} + \frac{3g}{2l} \phi$$

We put the second equation into the first one:

$$ (m_p + m_s) \ddot{x} = - \frac{1}{2} m_s (- \frac{3}{2} \ddot{x} + \frac{3g}{2} \phi) - b_p \dot x + F(s)$$

$$ (m_p + \frac{1}{4}m_s) \ddot{x} = \frac{3gm_s}{4} \phi - b_p \dot x + F(s)$$

$$\ddot{x} = \frac{1}{(m_p + \frac{1}{4}m_s)}\big(\frac{3gm_s}{4} \phi - b_p \dot x + F(s)\big)$$

Now we are only missing the equation for $`\ddot\phi`$

$$\ddot \phi = - \frac{3}{2l} \frac{1}{(m_p + m_s)}\big(- \frac{1}{2} m_s l \ddot \phi - b_p \dot x + F(s)\big) + \frac{3g}{2l} \phi$$

$$\big(1 - \frac{3m_s}{4(m_p+m_s)} \big)  \ddot \phi = \frac{3b_p}{2l(m_p+m_s)} \dot x - \frac{3}{2l(m_p + m_s)}F(s) + \frac{3g}{2l} \phi$$

$$\ddot \phi  = \frac{3b_p}{2l(m_p + \frac{1}{4}m_s)} \dot x + \frac{m_p+m_s}{m_p + \frac{1}{4}m_s}\frac{3g}{2l} \phi - \frac{3}{2l(m_p + \frac{1}{4}m_s)}F(s) $$

So if we now add all together my $`\italic{x}`$

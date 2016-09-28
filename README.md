# NetComp
A set of scripts designed to tackle computation tasks in network

1) DisSort
       <br>DisSort aims to tackle the problem of sorting of very large input files, that might take up a lot of time and memory for a single system. But distributing the task of sorting over a network of systems, we reduce the time complexity of out task to 
                                 <img src="http://www.sciweavers.org/tex2img.php?eq=%28n%2Fp%29log_2%28n%2Fp%29&bc=White&fc=Black&im=jpg&fs=18&ff=fourier&edit=0" align="center" border="0" alt="(n/p)log_2(n/p)" width="167" height="27" /> where n is the size of input, and p is the number of dedicated systems used to compute.<br>
       Yay!!,,,Now you can sort huge set of numbers at ease if you exploit the capabilities of a distributed system.

The branch coverage diagram for each version per experiment can be found below:
- [V3.10](v310.md)  
- [V4.14](v414.md)  
- [V5.0](v510.md)        
- [V5.2](v52.md)
- [V5.4](v54.md)    
- [V5.6](v56.md)    
- [V5.6-tsan](tsan.md)  
- [V5.9](v59.md)

Here we list the overall experiments results over 8 versions of rt-linux:

| RTOS Versions | Syzkaller | Moonshinez | \ufuzz   | average-impr | speedup     |
|---------------|-----------|------------|----------|--------------|-------------|
| 3.10-release  | 70597.8   | 68811.7    | 76566.4  | 8.5%/11.3%   | +2.1x/+1.8x |
| 4.14-release  | 55713.4   | 71789.2    | 107599.8 | 93.1%/49.9%  | +2.0x/+1.6x |
| 5.0-release   | 99694.2   | 109655.0   | 150821.4 | 51.3%/37.5%  | +1.5x/+1.7x |
| 5.2-release   | 216589.7  | 212443.6   | 245302.6 | 13.3%/15.5%  | +1.5x/+1.4x |
| 5.4-release   | 117011.6  | 119548.8   | 123333.4 | 5.4%/3.2%    | +1.6x/+1.7x |
| 5.6-ktsan     | 107028.4  | 109672.2   | 192071.8 | 79.5%/75.1%  | +2.2x/+2.0x |
| 5.6-release   | 123369.4  | 124085.4   | 126616.1 | 2.63%/2.04%  | +1.2x/+1.3x |
| 5.9-release   | 121085.2  | 125784.4   | 127003.6 | 4.89%/0.97%  | +1.5x/+1.1x |
| average       | 113886.2  | 117723.8   | 143664.4 | 26.1%/22.0%  | +1.7x/+1.6x |

<div align="center">
  <img src="https://github.com/Rtkaller/Rtkaller/blob/main/experiments/result.png" height="500px" alt="图片说明" >
</div>

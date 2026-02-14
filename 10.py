#Use f-strings , '.format()' , and '%' formatting to produce the same output -- discuss pros/cons.

Name = "Abir"
Age = 27
Cgpa = 2.81

output1= f"{Name} of age {Age} has got {Cgpa}"
print(output1)

output2 = "{} of age {} has got {}".format(Name,Age,Cgpa)
print(output2)

output3 = "%s of age %d has got %.1f" %(Name, Age, Cgpa)
print(output3)

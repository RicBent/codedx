import csv

out = open("profiles.html","w")

out.write(
"""<meta charset="utf-8" /> 

<style>
    table.profileTable
    {
        width: 100%;
        background-color: #FFFFFF;
        border-collapse: collapse;
        border-width: 2px;
        border-color: #2D4068;
        border-style: solid;
        color: #000000;
    }
    
    table.profileTable td, table.profileTable th
    {
        border-width: 2px;
        border-color: #2D4068;
        border-style: solid;
        padding: 4px;
    }
    
    table.profileTable thead
    {
        font-weight: bold;
        background-color: #374F7F;
        color: #FFFFFF;
    }
</style>\n\n""")


out.write("<table class=\"profileTable\">\n")

# column headers
out.write("<thead><tr><td>ID</td><td>ID</td><td>Name (jp)</td><td>Name (en)</td><td>Build function</td><td>Flags</td><td>ActorInfo[0]</td><td>ActorInfo[1]</td><td>ActorInfo[2]</td><td>ActorInfo[3]</td><td>ActorInfo[4]</td><td>ActorInfo[5]</td><td>ActorInfo[6]</td><td>ActorInfo[7]</td><td>ActorInfo[8]</td></tr></thead>\n")

with open('profiles.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, quotechar='\"')
    for row in reader:
        out.write('<tr>')
        for s in row:
            out.write('<td>%s</td>' % s)
        out.write('</tr>\n')

out.write("</table>\n")

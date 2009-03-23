#! /bin/sh

r=$(echo "scale=2; $4/$5*100." | bc)

echo "<tr height="15%">"
echo "<td align='center' valign='top'><font size=5 color=green>$7 </br></font></td>"
echo "<td align='center' valign='top'><font size=5 color=green>$1 s</br></font></td>"
echo "<td align='center' valign='top'><font size=5 color=green>$2 </br></font></td>"
echo "<td align='center' valign='top'><font size=5 color=green>$3 </br></font></td>"	
echo "<td align='center' valign='top'><font size=5 color=green>$4 ($r %) </br></font></td>"
echo "<td align='center' valign='top'><font size=5 color=green>$5 </br></font></td>"
echo "<td align='center' valign='top'><font size=5 color=green>$6 </br></font></td>"
echo "</tr>"

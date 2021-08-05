$fn=50;
wand=4*0.4;
X=38;
Y=38;
Z=31;
abstand=8;

union() {
difference() {
union() {
    cube([X+2*wand,Y+2*wand,wand]);
    translate([wand,wand,wand])cube([X,Y,wand]);
    }
translate([wand,2*wand,wand])cube([X,Y-2*wand,Z]);
}

translate([wand,wand,wand])cube([2*wand,2*wand,abstand]);
translate([X-wand,wand,wand])cube([2*wand,2*wand,abstand]);
translate([X-wand,Y-wand,wand])cube([2*wand,2*wand,abstand]);
}
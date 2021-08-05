$fn=50;
wand=4*0.4;
X=38;
Y=38;
Z=30;
rand=2;
bohrung=-5;
union() {
    
difference(){
    translate([-wand,-wand,-wand])cube([X+2*wand,Y+2*wand,Z+wand+rand]);
    union() {cube([X,Y,Z+rand]);
        translate([bohrung,0,0])cube([10,11,18]);
        translate([bohrung,Y-22,10])cube([10,9,4]);
        translate([bohrung,5,Z-3-1.5])rotate([0,90,0])cylinder(d=6,h=10);
    }
}
translate([0,4,Z-11])rotate([0,0,-90])tri_angle(4,4,2);
translate([X-4,0,Z-11])rotate([0,0,0])tri_angle(4,4,2);
translate([4,Y,Z-11])rotate([0,0,-180])tri_angle(4,4,2);
translate([X,Y-4,Z-11])rotate([0,0,90])tri_angle(4,4,2);
}

module tri_angle(a, b, wall, direction=0)
{
    myPoints=[
    [[0,0],[a,0],[a,b]],
    [[0,0],[a,0],[0,b]],
    [[0,0],[a,0],[0,b]],
    [[0,0],[a,0],[0,b]]
    ];
    myRotate=[
    [0,0,0],
    [0,0,0],
    [90,0,0],
    [90,0,90]
    ];
    
    rotate(myRotate[direction])
        linear_extrude(height = wall) 
            polygon( points=myPoints[direction]);
}

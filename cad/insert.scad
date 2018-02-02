use <fillets.scad>
union()
{
    base(83,2,4,8);
    translate([-83/2+2,0,2])
    {
        rotate([0,-90,0])
            snaps(19,5,2,2,2);
    }
    translate([83/2-2,0,2])
    {
        rotate([0,-90,-180])
            snaps(19,5,2,2,2);
    }
    translate([0,0,-2])
        cylinder(h = 2,d =85);
}


module base(ID,CH,RW,RL)
{
    difference()
    {
        cylinder(h = CH, d = ID);
        translate([0,ID/2-RW,0])
        cube([RW,RL,CH +3],center= true);
    }
}

module snaps(L,W,D,FW,R)
{
    union()
    {
        translate([L/2,0,D/2])
        union()
        {
            cube([L,W,D],center = true);
            translate([L/2 - R,0,(D/2)])
            halfsphere(R);
        }
        translate([FW,-W/2,-FW])
        {
            rotate([90,0,90])
                fil_linear_o(W,FW,angle = 90);
        }
    }
}

module halfsphere(R)
{
    difference()
        {
            sphere(r = R);
            translate([0,0,-R])
            cube([2*R,2*R,2*R],center = true);
        }
}

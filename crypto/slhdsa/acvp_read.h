/* Length-prefixed, big-endian fields in the offline ACVP fixtures. */
static uint32_t read_u32(void) {
    uint8_t b[4];
    assert(fread(b,1,4,stdin)==4);
    return (uint32_t)b[0]<<24 | (uint32_t)b[1]<<16 | (uint32_t)b[2]<<8 | b[3];
}
static octets_t field(void) {
    uint32_t n=read_u32();
    assert(n < (1u<<28));
    octets_t x=new_octets();
    x->length=n;
    x->seq=new_octet_array(n);
    assert(fread(x->seq->elems,1,n,stdin)==n);
    return x;
}

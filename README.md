srsRAN
======

To edit the bands requested as part of UE capability, edit the file found at `srsenv/src/stack/rrc/rrc_ue.cc`.

You can set the bands on line 1086 and 1095 -- about 15 lines in to the `send_ue_cap_enquiry` function.

After doing so, run:

```
mkdir build
cd build
cmake ../
sudo make
sudo make install
sudo srsenb
```

This builds and launches srsRAN's eNB. Config files can be edited normally (usually in `/root/.config/srsran/...`).

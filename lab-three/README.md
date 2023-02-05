# lab-three

## Principles of Secure Communication

**1. Do you think that it is a significant risk that such metadata is exposed when using TLS over TCP for Internet
communications?**

Yes, I think it is a significant security risk that headers are not encrypted when using TLS over TCP.
My main reasoning is because those headers contain where the packets came from and where the packets are going to.

While the main data during transit is encrypted with TLS. It offers, in my opinion, almost no benefit if the endpoints
are not correctly protected against malicious attacks. A malicious attacker could snoop on the packets during transit
and then choose to attack either endpoint... rendering the encryption via TLS worthless.

Future protocols MUST be encrypted end-to-end. Without encrypting all the data, people will assume constants from
packets and therefore, hurt the deploy-ability and evolve-ability of the protocol itself.

## Transport Layer Security (TLS) v1.3

**1. What hope do we have to extend and modify the design of the Internet if an essential protocol like TLS, used by
almost every web browser and web server in the world, is so hard to upgrade?**

_None._

Jokes aside, future designs of communication protocols must be flexible but also exercise their right to be flexible.
Proposals like GREASE should allow implementers of TLS to implement TLS in their servers as intended and not assume that
certain fields are constant when in reality they aren't.

I also firmly believe that there needs to be better feedback loops, granted that this is a lot easier said than done. A fast
feedback loop that correctly tells implementers that their implementation of TLS or [insert protocol] is buggy would be
extremely beneficial, and I'd imagine would really help in reducing buggy or inaccurate implementations of network
protocols at an internet scale.

**2. Does the proposal for GREASE described in the blog post make sense?**

Yes, the proposal makes sense. On a personal note, it's _very_ interesting to me that people assumed certain fields were
constant when in reality, they were actually flexible but hadn't been... 'flexed' until that point.

**3. What, if anything, has changed around the deployment of TLS 1.3 in the five years since that blog post was 
written**

I don't think anything has primarily changed? _I could be wrong - more research needed_

# Notes

QUIC was designed on top of UDP because they wanted to avoid the technical debt of TCP. Avoiding TCP allows QUIC to be
deployable _TODAY_.
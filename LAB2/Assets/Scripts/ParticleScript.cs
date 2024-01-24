using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleScript : MonoBehaviour
{
    public class SingleParticle
    {
        public Vector3 force;
        public float ttl;
        public float start;
        public Rigidbody obj;
       

        public SingleParticle(Rigidbody obj, float start)
        {
            this.obj = obj;
            this.force = new Vector3(Random.Range(-5f, 5f), Random.Range(4f, 6f), Random.Range(-5f, 5f));
            this.ttl = Random.Range(0.5f, 1.5f);
            this.start = start;
            float scale_obj = Random.Range(-0.5f, 0.5f);
            Vector3 scale_v = new Vector3(scale_obj, scale_obj, scale_obj);
            this.obj.transform.localScale += scale_v;   
        }
    }
}

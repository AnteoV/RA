using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SystemHandler : MonoBehaviour
{
    public Rigidbody o;
    public GameObject pos;
    public Material[] materials = new Material[5];
    private List<ParticleScript.SingleParticle> lista;
    private static float timer;

    // Start is called before the first frame update
    void Start()
    {
        timer = 0.0f;
        lista = new List<ParticleScript.SingleParticle>(50);

        for (int i=0; i<50; i++)
        {
            addProcedure(lista);
        }
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;

        for(int i=0; i<50; i++)
        {
            if(timer > lista[i].ttl + lista[i].start)
            {
                Destroy(lista[i].obj.gameObject);
                lista.Remove(lista[i]);
                addProcedure(lista);
            }
        }

        moveProcedure();

    }

    private void forceProcedure(ParticleScript.SingleParticle p)
    {
        p.obj.AddForce(p.force.x, p.force.y, p.force.z, ForceMode.Impulse);
    }

    private void addProcedure(List<ParticleScript.SingleParticle> l)
    {
        Transform t = pos.transform;
        Rigidbody rb_temp = Instantiate(o, t.position, Quaternion.identity) as Rigidbody;
        int colorpick = (int)Mathf.Ceil(Random.Range(0.01f, 4.99f)) - 1;
        rb_temp.gameObject.GetComponent<Renderer>().material = materials[colorpick];
        ParticleScript.SingleParticle ps = new ParticleScript.SingleParticle(rb_temp, timer);
        l.Add(ps);
        forceProcedure(ps);
    }

    private void moveProcedure()
    {
        float x = 5*Mathf.Sin(timer);
        float y = 0;
        float z = 5*Mathf.Cos(timer);
        pos.transform.position = new Vector3(x, y, z);
    }
}

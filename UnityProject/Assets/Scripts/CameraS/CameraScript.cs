using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour
{

    public GameObject player;
    public float offset;

    // Start is called before the first frame update
    void Start()
    {
        this.transform.position = new Vector3(21, 40, -21);
    }

    // Update is called once per frame
    void Update()
    {
        //this.transform.position = player.transform.position + Vector3.up * offset;
        
    }
}

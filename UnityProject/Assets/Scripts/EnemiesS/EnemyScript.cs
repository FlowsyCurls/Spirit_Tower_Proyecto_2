using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyScript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }
    public void moveTo(float row, float column)
    {
        this.transform.localPosition = new Vector3(row, 1f, column);
    }
}

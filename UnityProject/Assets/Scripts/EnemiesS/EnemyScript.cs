using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyScript : MonoBehaviour
{
    // Start is called before the first frame update

    public float row;
    public float column;
   
    //public float speed;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float step = 3.5f * Time.deltaTime;
        Vector3 destino = new Vector3(row, 1f, column);

        if (transform.position.x != destino.x || transform.position.z != destino.z)
        {
            transform.position = Vector3.MoveTowards(transform.position, destino, step);
        }
        
    }
    public void moveTo(float _row, float _column)
    {

        if (_row != row || _column != column)
        {

            row = _row;
            column = _column;

            //this.transform.localPosition = new Vector3(row, 1f, column);

        }
    }
}

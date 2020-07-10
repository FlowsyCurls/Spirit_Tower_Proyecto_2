using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class backTrigger : MonoBehaviour
{

    public GameObject targetEnemy;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Player") {
            Debug.Log("Ataca jugador por espalda");
            Destroy(targetEnemy);
        }
    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackS : MonoBehaviour
{
    public Transform player;
    public bool isAttacking;
    private float attackTime;
    private Vector3 originalSize;

    private void Start()
    {
        originalSize = transform.localScale;
        isAttacking = false;
        attackTime = 1f;
    }

    private void Update()
    {

        if (Input.GetKeyDown(KeyCode.E))
        {
            attackTime = Time.time + 1;
            isAttacking = true;
        }

        if (Time.time >= attackTime)
        {
            isAttacking = false;
        }

        if (isAttacking)
        {
            this.transform.localScale = originalSize + new Vector3(.5f,0,0);
            this.transform.position = player.position + player.transform.right;
        }
        else {
            this.transform.localScale = originalSize;
            this.transform.position = player.position;
        }

        
    }

}

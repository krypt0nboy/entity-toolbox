<?php

/**
 * Created by PhpStorm.
 * User: ddoucoure
 * Date: 08/08/16
 * Time: 10:56
 */

class SchemaBuilder extends ContribHookBuilder {
  
  public function __construct($entity_type , array $values) {
    $this->hook = 'schema';
    parent::__construct($this->hook, $entity_type, $values);
  }
  
  public function defaultBaseSchema(){
    return array(
      'description' => 'The base table for ' . $this->entityType,
      'fields' => array(
        'id' => array(
          'type' => 'serial',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => '',
        ),
        'vid' => array(
          'description' => 'The current ' . $this->entityType . ' version identifier.',
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => FALSE,
          'default' => NULL,
        ),
        'label' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => FALSE,
          'default' => '',
          'description' => 'The label of this ' . $this->entityType,
        ),
        'uid' => array(
          'description' => 'The {users}.uid that created this ' . $this->entityType,
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
        'created' => array(
          'description' => 'The Unix timestamp when the ' . $this->entityType . ' was created.',
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
        'changed' => array(
          'description' => 'The Unix timestamp when the ' . $this->entityType . ' was most recently saved.',
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
      ),
      'indexes' => array(
        $this->entityType . '_changed'  => array('changed'),
        $this->entityType . '_created'  => array('created'),
        $this->entityType . '_uid'      => array('uid'),
      ),
      'unique keys' => array(),
      'foreign keys' => array(
        $this->entityType . '_author' => array(
          'table' => 'users',
          'columns' => array('uid' => 'uid'),
        ),
        $this->entityType . '_revision' => array(
          'table' => $this->entityType . '_revision',
          'columns' => array('vid' => 'vid'),
        ),
      ),
      'primary key' => array('id'),
    );
  }
  
  public function defaultRevisionSchema(){
    return array(
      'description' => 'Stores information about each saved version of a ' . $this->entityType,
      'fields' => array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'default' => 0,
        ),
        'vid' => array(
          'description' => 'The primary identifier for this version.',
          'type' => 'serial',
          'unsigned' => TRUE,
          'not null' => TRUE,
        ),
        'uid' => array(
          'description' => 'The {users}.uid that created this version.',
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
        'label' => array(
          'description' => 'The label of this version.',
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'default' => '',
        ),
        /*'log' => array(
          'description' => 'The log entry explaining the changes in this version.',
          'type' => 'text',
          'not null' => TRUE,
          'size' => 'big',
        ),*/
        'timestamp' => array(
          'description' => 'A Unix timestamp indicating when this version was created.',
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
        ),
      ),
      'indexes' => array(
        $this->entityType . 'id' => array('id'),
        'uid' => array('uid'),
      ),
      'primary key' => array('vid'),
      'foreign keys' => array(
        'versioned_' . $this->entityType => array(
          'table' => $this->entityType,
          'columns' => array('id' => 'id'),
        ),
        'version_author' => array(
          'table' => 'users',
          'columns' => array('uid' => 'uid'),
        ),
      ),
    );
  }
  
  
  public function defaultSchemaBuilderRelation(){
    
  }
  
  public function defaultSchemaBuilderRelationRevision(){
    
  }
  
}
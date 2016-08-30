<?php

/**
 * Class SchemaModel
 */
class SchemaModel extends HookModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'description'  => array(
            'type'   => 'string',
            'method' => 'buildDescription',
          ),
          'fields'       => array(
            'type'    => 'array',
            'method'  => 'buildFields',
            'default' => '',
            'model'   => 'schema_field_model'
          ),
          'unique keys'  => array(
            'type'   => 'array',
            'method' => 'buildUniqueKeys',
          ),
          'foreign keys' => array(
            'type'    => 'array',
            'method'  => 'buildForeignKeys',
            'default' => '',
            'model'   => ''
          ),
          'indexes'      => array(
            'type'    => 'array',
            'method'  => 'buildIndexes',
            'default' => '',
            'model'   => ''
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}
<?php

/**
 * Class DrupalSchemaModel
 */
class DrupalSchemaModel extends SchemaRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'description'  => array(
            'type'    => 'string',
            'method'  => 'buildDescription',
          ),
          'fields'       => array(
            'type'   => 'array',
            'method' => 'buildFields',
          ),
          'unique keys'  => array(
            'type'   => 'array',
            'method' => 'buildUniqueKeys',
          ),
          'foreign keys' => array(
            'type'   => 'array',
            'method' => 'buildForeignKeys',
          ),
          'primary keys' => array(
            'type'   => 'array',
            'method' => 'buildPrimaryKey',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}
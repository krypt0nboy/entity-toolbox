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
            'type'   => 'string',
            'method' => 'buildDescription',
          ),
          'fields'       => array(
            'type'   => 'array',
            'method' => 'buildFields',
          ),
          'unique keys'  => array(
            'type'     => 'array',
            'method'   => 'buildUniqueKeys',
            'unset if' => 'is_empty:c:'
          ),
          'foreign keys' => array(
            'type'     => 'array',
            'method'   => 'buildForeignKeys',
            'unset if' => 'is_empty:c:'
          ),
          'primary keys' => array(
            'type'     => 'array',
            'method'   => 'buildPrimaryKey',
            'unset if' => 'is_empty:c:'
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}
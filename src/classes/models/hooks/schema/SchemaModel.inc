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
            'type'   => 'array',
            'method' => 'buildFields',
            'model'  => 'schema_field_model'
          ),
          'unique keys'  => array(
            'type'     => 'array',
            'method'   => 'buildUniqueKeys',
            'unset if' => 'empty:c:'
          ),
          'foreign keys' => array(
            'type'     => 'array',
            'method'   => 'buildForeignKeys',
            'unset if' => 'empty:c:'
          ),
          'indexes'      => array(
            'type'     => 'array',
            'method'   => 'buildIndexes',
            'unset if' => 'empty:c:'
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}
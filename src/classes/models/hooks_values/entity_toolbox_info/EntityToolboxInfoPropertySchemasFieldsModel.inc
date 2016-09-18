<?php

/**
 * Class EntityToolboxInfoPropertySchemasFieldsModel
 */
class EntityToolboxInfoPropertySchemasFieldsModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'schemas_fields',
        'structure' => array(
          'base'              => array(
            'type'   => 'array',
            'method' => 'buildBaseSchemasFields',
          ),
          'revision'          => array(
            'type'   => 'array',
            'method' => 'buildRevisionSchemasFields',
          ),
          'relation'          => array(
            'type'   => 'array',
            'method' => 'buildRelationSchemasFields',
          ),
          'relation_revision' => array(
            'type'   => 'array',
            'method' => 'buildRelationRevisionSchemasFields',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}
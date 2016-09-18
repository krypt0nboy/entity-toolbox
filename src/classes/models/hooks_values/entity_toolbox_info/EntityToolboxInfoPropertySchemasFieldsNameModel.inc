<?php

/**
 * Class EntityToolboxInfoPropertySchemasFieldsNameModel
 */
class EntityToolboxInfoPropertySchemasFieldsNameModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'schemas_fields_name',
        'structure' => array(
          'base'              => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_name_base%',
          ),
          'revision'          => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_name_revision%',
          ),
          'relation'          => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_name_relation%',
          ),
          'relation_revision' => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_name_relation_revision%',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}